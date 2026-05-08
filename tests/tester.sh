#!/bin/bash

echo "This tester will test all .cub maps included in the maps/ directory."
echo "When the game runs, press ESC or close the window to continue."

LOG_DIR="tests/valgrind_logs"
mkdir -p "$LOG_DIR"

for fd in /proc/$$/fd/*; do
	fd_num=${fd##*/}
	if [ "$fd_num" -gt 2 ] 2>/dev/null; then
		eval "exec $fd_num>&-" 2>/dev/null
	fi
done

if [ ! -x "./cub3D_bonus" ]; then
	echo "Error"
	echo "./cub3D_bonus not found or not executable. Run: make bonus"
	exit 1
fi

find maps -type f -name "*.cub" | sort | while read -r map; do
	log="$LOG_DIR/$(echo "$map" | tr '/.' '__').log"
	echo "Testing map: $map"
	output=$(valgrind --leak-check=full --show-leak-kinds=all \
		--track-fds=yes --track-origins=yes ./cub3D_bonus "$map" 2>&1)
	printf "%s\n" "$output" > "$log"

	if echo "$output" | grep -q "Error"; then
		echo "$output" | grep -A 1 "Error"
	fi

	if echo "$output" | grep -q "ERROR SUMMARY: [1-9]"; then
		echo "Valgrind errors found. Full log: $log"
		echo "$output" | grep -E -B 2 -A 25 \
			"Conditional jump|Syscall param|points to uninitialised|depends on uninitialised|Use of uninitialised|uninitialised value|Uninitialised|Invalid read|Invalid write|Invalid free|Mismatched|ERROR SUMMARY"
	fi

	if echo "$output" | grep -q "lost: [1-9]"; then
		echo "$output" | grep -A 20 "LEAK SUMMARY"
	elif echo "$output" | grep -q "still reachable"; then
		echo "$output" | grep -A 5 "still reachable"
	fi

	if echo "$output" | grep -q "Open file descriptor"; then
		echo "$output" | grep -A 10 "Open file descriptor"
	fi
done
