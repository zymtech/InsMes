LDFLAGS += -L /usr/local/lib/

all:
	gcc register.c -o register -lsqlite3 $(LDFLAGS)
	gcc login.c -o login -lsqlite3 $(LDFLAGS)
	gcc add_friend.c -o add_friend -lsqlite3 $(LDFLAGS)
	gcc talk.c -o talk -lsqlite3 $(LDFLAGS)
	gcc record.c -o record -lsqlite3 $(LDFLAGS)
	gcc server.c -o server $(LDFLAGS)
