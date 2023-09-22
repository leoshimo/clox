CC=clang
CFLAGS=-I -Wall -Werror -std=c99

help:	## Show Help
	@grep --no-filename -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-15s\033[0m %s\n", $$1, $$2}'

run: clox ## Run clox
	./clox

build: clox ## Build clox

clox: main.o chunk.o memory.o value.o vm.o
	$(CC) -o $(@) $^

format: ## Format
	clang-format -i *.{h,c}

clean: ## Clean
	rm *.o
