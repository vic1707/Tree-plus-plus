ACTIONS = all fclean re
APPS = cpp go v

OUT_DIR = $(PWD)/bin/

.PHONY: $(ACTIONS)

$(ACTIONS):
	@for app in $(APPS); do $(MAKE) -C $$app $@ OUT_DIR="$(OUT_DIR)"; done
