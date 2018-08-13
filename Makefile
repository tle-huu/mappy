all:
	make -C server
	make -C client
	cd gfx && sh deps.sh && make

clean:
	make -C server clean
	make -C server lclean
	make -C client clean
	make -C gfx clean

fclean: clean
	make -C server fclean
	make -C server lfclean
	make -C client fclean
	make -C gfx fclean

re: fclean all
