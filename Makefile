search-test: search-test.c
	gcc -o $@ $^

archlinux/root-image.fs: search-test
	sudo mount -o loop $@ root/ && sudo cp $^ root/ && sudo umount root/

run: archlinux/root-image.fs
	$(MAKE) --directory linux ARCH=um linux
	linux/linux ubda=archlinux/root-image.fs mem=1G init=/search-test
