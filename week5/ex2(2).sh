# Roman Soldatov BS19-02
# Exercise 2

# This is modified script to prevent the race!

# Produce a file of sequential numbers
# Check if file exist
# The file which will contain numbers has a name ex2.txt
if [ ! -f $"ex2.txt" ]	
then
	# If this file does not exit, then create it with initial value 0
	echo 0 > $"ex2.txt"	
fi

# Calculate sequential numbers.
# Add the new number on each iteration.

# Set N value to not let it loop forever
N=1000

# Last number to add at the end of a file
number=0
while [[ $N -gt $number ]]; do
	
   	# To not let the race condition happen
	# We lock the current process (go to the next iteration in this case)
	# while the file ex2.lock exists
	if ln ex2.txt ex2.lock; then 
        	# Read a last element from ex2.txt and write into the number variable
       		number=`tail -n 1 ex2.txt`

		# In case another process has already completed the insertion
        	if [ $number -ge $N ]; then 
			# Remove ex2.lock
        		rm ex2.lock

        		break
        	fi

        	# Increment the last number
		((number++))

		# Write incremented number into ex2.txt
		echo $number >> ex2.txt    

		# Remove ex2.lock
		# We show for other processes that we lived the critical region
        	rm ex2.lock
	fi
done