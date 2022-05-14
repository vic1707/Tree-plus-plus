ACTIONS = all fclean re
APPS = cpp go v

.PHONY: $(ACTIONS)

$(ACTIONS):
	@for app in $(APPS); do make -C $$app $@; done
