src_dir := ./src
bin_dir := ./bin
lab1_shared_dir := $(shell pwd)/labs/two_hosts_direct/shared
lab2_shared_dir := $(shell pwd)/labs/six_hosts_two_routers/shared

CC := gcc



all: iperfer

iperfer:
	$(CC) $(src_dir)/iperfer.c -o $(bin_dir)/iperfer
	cp -f $(bin_dir)/iperfer $(lab1_shared_dir)
	cp -f $(bin_dir)/iperfer $(lab2_shared_dir)

compile:
	$(CC) $(src_dir)/iperfer.c -o $(bin_dir)/iperfer

compile-w:
	$(CC) $(src_dir)/iperfer.c -o $(bin_dir)/iperfer -lws2_32

clean:
	rm -f $(bin_dir)/iperfer $(lab1_shared_dir)/iperfer $(lab2_shared_dir)/iperfer

commit:
	git add .
	@read -p "commit message: " msg; \
	git commit -m "$$msg"
	git status

