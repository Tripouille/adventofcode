gcc day7_part2.c -o ampli_part2

max_value=0

ampli1=5
while [ $ampli1 -le 9 ]
	do
	ampli2=5
	while [ $ampli2 -le 9 ]
		do
		if [ $ampli1 -eq $ampli2 ]
			then
			((ampli2++))
			continue
		fi
		ampli3=5
		while [ $ampli3 -le 9 ]
			do
			if [ $ampli1 -eq $ampli3 ] || [ $ampli2 -eq $ampli3 ]
				then
				((ampli3++))
				continue
			fi
			ampli4=5
			while [ $ampli4 -le 9 ]
				do
				if [ $ampli1 -eq $ampli4 ] || [ $ampli2 -eq $ampli4 ] || [ $ampli3 -eq $ampli4 ]
					then
					((ampli4++))
					continue
				fi
				ampli5=5
				while [ $ampli5 -le 9 ]
					do
					if [ $ampli1 -eq $ampli5 ] || [ $ampli2 -eq $ampli5 ] || [ $ampli3 -eq $ampli5 ] || [ $ampli4 -eq $ampli5 ]
						then
						((ampli5++))
						continue
					fi
					prev_ampli=$(echo $ampli1$ampli2$ampli3$ampli4$ampli5 | ./ampli_part2 day7_input.txt)
					((ampli5++))
					#echo $prev_ampli
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

