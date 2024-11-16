## Find the targets (If they exist)
# Test: solution.h + solution.cpp + test.cpp
TEST_TARGETS = $(wildcard *.cc)
# Lib targets: *.cc inside mesh folder
LIB_TARGETS = $(shell find . -path "./mesh/*.cc")

# output
OUTPUT = solution.out

## Compile
COMPILE_FLAGS = -std=c++2a -lgtest -lgtest_main -pthread
## Inlcude flas
INCLUDE_LIB_FLAGS = -I ./mesh

## Docker
IMAGE_NAME = ubuntu-grafica
IMAGE_VERSION = 1

test: check_image ## Run the tests
	docker run -v $(shell pwd):/workdir -w /workdir -it  $(IMAGE_NAME):$(IMAGE_VERSION) bash -c "make build_test && ./$(OUTPUT)"

build_test: ## Build the test executable
	g++ -o $(OUTPUT) $(INCLUDE_LIB_FLAGS)  $(LIB_TARGETS) $(TEST_TARGETS) $(COMPILE_FLAGS) 

build_image: ## Build the docker image that will be used to compile and test the files
	@docker build . -f Dockerfile -t  $(IMAGE_NAME):$(IMAGE_VERSION) --build-arg uid=$(shell id -u) --build-arg gid=$(shell id -g) --build-arg user=dockeruser --build-arg group=dockergroup

check_image: ## Verify if the docker image exists. Otherwise, build it
	docker image inspect $(IMAGE_NAME):$(IMAGE_VERSION) > /dev/null 2>&1 || make build_image

remove_image: ## Forcefully delete the docker image
	@docker ps -a -q --filter ancestor=ubuntu-grafica:1 | xargs -r docker rm -f
	@docker rmi -f ubuntu-grafica:1

shell: check_image ## Launch a bash attached to the docker image that already contains GTest and the tools needed to build the code
	docker run -v $(shell pwd):/workdir -w /workdir -it $(IMAGE_NAME):$(IMAGE_VERSION) bash

