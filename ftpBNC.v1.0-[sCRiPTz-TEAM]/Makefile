CFLAGS := -O3 -Wall -Wextra
LIBS := -lpthread
ftpBNC_OBJS := main.o server.o client.o config.o misc.o ident.o xtea.o hex.o
CONF_OBJS := makeconf.o config.o misc.o hex.o xtea.o

ifeq ($(wildcard conf.h),)
$(shell echo "#undef CONF_EMBEDDED" > conf.h)
CONF_EMBEDDED := false
else
CONF_EMBEDDED := true
endif

all: ftpBNC
ftpBNC: $(ftpBNC_OBJS)
	$(CC) $(CFLAGS) $(ftpBNC_OBJS) -o ftpBNC $(LIBS)
	@echo "------------------------------------------------------- --- -> >"
	@echo "ftpBNC built successfully"
	@echo "------------------------------------------------------- --- -> >"
	@if [ "$(CONF_EMBEDDED)" = "true" ]; then \
		echo "Run './ftpBNC' to start the bouncer."; \
	else \
		echo "Edit ftpBNC.conf to suit your needs, "; \
    echo "then run './ftpBNC ftpBNC.conf' to start the bouncer."; \
	fi
	@echo "------------------------------------------------------- --- -> >"

conf: $(CONF_OBJS)
	$(CC) $(CFLAGS) $(CONF_OBJS) -o makeconf
	@./makeconf

%.o: %.c
	$(CC) -c $(CFLAGS) -MD -o $@ $<

-include $(ftpBNC_OBJS:.o=.d)
-include $(CONF_OBJS:.o=.d)

clean:
	@rm -f *.o *.d ftpBNC conf.h makeconf
	
