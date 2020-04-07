if gcc covid.c -lcurl;
then
	echo compiled sucesfully!
	echo running...
	cat art.txt                                                   
	./a.out		                                                     
else
	echo
	echo compilation failed
	echo
fi

