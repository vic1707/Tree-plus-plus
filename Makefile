APPS = cpp go v

.PHONY: all fclean re

all:
	for app in $(APPS); do make -C $$app; done

fclean:
	for app in $(APPS); do make -C $$app fclean; done

re: fclean all
