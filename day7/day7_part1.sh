gcc day7_part1.c -o ampli_part1

max_value=0

ampli1=0
while [ $ampli1 -le 4 ]
	do
	ampli2=0
	while [ $ampli2 -le 4 ]
		do
		if [ $ampli1 -eq $ampli2 ]
			then
			((ampli2++))
			continue
		fi
		ampli3=0
		while [ $ampli3 -le 4 ]
			do
			if [ $ampli1 -eq $ampli3 ] || [ $ampli2 -eq $ampli3 ]
				then
				((ampli3++))
				continue
			fi
			ampli4=0
			while [ $ampli4 -le 4 ]
				do
				if [ $ampli1 -eq $ampli4 ] || [ $ampli2 -eq $ampli4 ] || [ $ampli3 -eq $ampli4 ]
					then
					((ampli4++))
					continue
				fi
				ampli5=0
				while [ $ampli5 -le 4 ]
					do
					if [ $ampli1 -eq $ampli5 ] || [ $ampli2 -eq $ampli5 ] || [ $ampli3 -eq $ampli5 ] || [ $ampli4 -eq $ampli5 ]
						then
						((ampli5++))
						continue
					fi
					prev_ampli=0
					prev_ampli=$(echo $ampli1 | ./ampli_part1 day7_input.txt $prev_ampli)
					prev_ampli=$(echo $ampli2 | ./ampli_part1 day7_input.txt $prev_ampli)
					prev_ampli=$(echo $ampli3 | ./ampli_part1 day7_input.txt $prev_ampli)
					prev_ampli=$(echo $ampli4 | ./ampli_part1 day7_input.txt $prev_ampli)
					prev_ampli=$(echo $ampli5 | ./ampli_part1 day7_input.txt $prev_ampli)
					((ampli5++))
					if [ $prev_ampli -gt $max_value ]
						then
						max_value=$prev_ampli
					fi
				done
				((ampli4++))
			done
			((ampli3++))
		done
		((ampli2++))
	done
	((ampli1++))
done
echo "$max_value"

