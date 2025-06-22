CC = gcc
CFLAGS = -Wall -Wextra
TARGETS = fork_demo process_work data_copy file_sharing dumbsh wait_demo multiple_forks double_fork

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS) shared.txt
