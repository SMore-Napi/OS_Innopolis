# Roman Soldatov BS19-02
# Exercise 2

# How long does it take before a race condition manifests itself? 
# What is the critical region?

# Well, the race condition might happen randomly, 
# because it happens at the moment when another process executes on a critical region,
# but the first hasn't finished incrementing the last value and writing it.
# I got the race condition immediately: I had 0, 1, 1, 2, 2, ... in the output file,
# i.e. background and foreground processes read the last value and both incremented this old value without any synchronization on each other.
# Also, I got this sequence: 106, 107, 108, 107 108, 109, ..., 
# which means that one process was writing an old increment value while another has already incremented it and was on the next step. And it happened that both of them were writing their value at the same time. So, on the i-th line I got two numbers instead of one

# Here, the critical region is the reading the last value from a file, incrementing it and writing to the end of this file

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
	
        # Read a last element from ex2.txt and write into the number variable
       	number=`tail -n 1 ex2.txt`

        # Increment the last number
	((number++))

	# Write incremented number into ex2.txt
	echo $number >> ex2.txt    
done