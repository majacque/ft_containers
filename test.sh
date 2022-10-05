#!/bin/bash

echo "Compiling..."
make ft_container.out > /dev/null
if [ $? -ne 0 ]; then
	exit 1
fi

make std_container.out > /dev/null
if [ $? -ne 0 ]; then
	exit 1
fi

echo "Running..."
if [ $# -gt 0 ]; then
	/usr/bin/time -pao ft.log ./ft_container.out $1 > ft.log
	/usr/bin/time -pao std.log ./std_container.out $1 > std.log
else
	/usr/bin/time -pao ft.log ./ft_container.out > ft.log
	/usr/bin/time -pao std.log ./std_container.out > std.log
fi

echo "Diff:"
diff ft.log std.log
