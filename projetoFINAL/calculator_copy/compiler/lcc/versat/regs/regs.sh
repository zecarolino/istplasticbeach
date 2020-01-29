for i in 0 1 2 3 4 5 6 7 8 9 10 11 12; do
	echo -n "R$i: "
	grep R${i}$ $1 | wc -l
done
grep "POP r" $1 | awk '{ print $NF }' | sort | uniq | xargs
grep used= $1
