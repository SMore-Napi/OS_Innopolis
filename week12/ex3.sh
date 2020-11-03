# Roman Soldatov BS19-02
# Exercise 3

# Create two files from which we will copy
# file1 has 1MB size
# file100 has 100MB size
for i in 1 100
do
	dd if=/dev/zero of=file$i bs=$(($i*1024*1024)) count=1
done

# Experiment with different file and buffer sizes
for k in 16 1024
do
	# Set the buffer size while compiling
	echo "BUFFER SIZE = $k bytes"
	gcc -DBUF_SIZE=$k -o copy1 copy.c
	gcc -DBUF_SIZE=$k -DSYNC=1 -o copy2 copy.c

	# Check time for different files
	for i in 1 100
	do
		echo "File size = $i MB"
		# Check with and without O_SYNC flag
		echo "O_SYNC"
		time ./copy2 file$i newFile
		echo "No O_SYNC"
		time ./copy1 file$i newFile
	done
done

# Remove temporary files
rm file{1,100} copy{1,2} newFile
