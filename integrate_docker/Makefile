include config.mk


all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OUT)

#feature support build in docker

IN_DOCKER:=$(shell test -f /integrate_docker/Makefile && echo 1)
$(info IN_DOCKER = $(IN_DOCKER)) 

ifeq (,$(IN_DOCKER))
BUILD_DOCKER_NAME=ubuntu
BUILD_DOCKER_VERSION=latest
# CCACHE_MOUNT:=-v /ccache:/ccache
MAKE_PID:=$(shell echo $$PPID)
$(info MAKE_PID = $(MAKE_PID)) 
MAKE_CMD:=$(shell xargs -0 < /proc/$(MAKE_PID)/cmdline)
$(info MAKE_CMD = $(MAKE_CMD)) 
$(info MAKE_PID = $(MAKE_PID))

CREATE_BUILD_DOCKER_USER = \
	echo "Building with docker_ver=$(BUILD_DOCKER_VERSION)"; \
	docker build --no-cache \
		--progress=plain \
		--build-arg docker_ver=$(BUILD_DOCKER_VERSION) \
		--build-arg user=$(USER) \
		--build-arg uid=1010 \
		--build-arg guid=1010 \
		-t $(BUILD_DOCKER_NAME)-$(USER):$(BUILD_DOCKER_VERSION) \
		-f $(PROJECT_PATH)/../env/docker/Dockerfile.user \
		$(PROJECT_PATH)/../env/docker/

# Build an image from this project
build_docker:
	@if ! docker inspect --type=image $(BUILD_DOCKER_NAME):$(BUILD_DOCKER_VERSION) >/dev/null 2>&1; then \
		echo "Pulling base image..."; \
		docker pull $(BUILD_DOCKER_NAME); \
	fi;
	@if ! docker inspect --type=image $(BUILD_DOCKER_NAME)-$(USER):$(BUILD_DOCKER_VERSION) >/dev/null 2>&1; then \
		echo "Creating user-specific build image..."; \
		$(CREATE_BUILD_DOCKER_USER); \
	fi;

.PHONY: build_docker

# Define Docker run commands
RUN_BUILD_DOCKER = docker run --rm --privileged --init \
	-u $(id -u):1010  -v $(PROJECT_PATH):/integrate_docker \
	--tmpfs /tmp:exec \
	-v ~/.ssh:/var/$(USER)/.ssh \
	-e OS_DEV_DIR=/integrate_docker \
	-w /integrate_docker \
	$(BUILD_DOCKER_NAME)-$(USER):$(BUILD_DOCKER_VERSION)

RUN_BUILD_DOCKER_IT = docker run \
	-w /integrate_docker -it \
	--privileged --init \
	-u kali:1010  -v $(PROJECT_PATH):/integrate_docker \
	--tmpfs /tmp:exec \
	-v ~/.ssh:/var/$(USER)/.ssh \
	-e OS_DEV_DIR=/integrate_docker \
	-e COLUMNS="`tput cols`" \
	-e LINES="`tput lines`" \
	$(BUILD_DOCKER_NAME)-$(USER):$(BUILD_DOCKER_VERSION)

# Determine interactive mode
ifneq ($(shell tty 2>/dev/null),)
	BUILDER = $(RUN_BUILD_DOCKER_IT)
else
	BUILDER = $(RUN_BUILD_DOCKER)
endif

$(info BUILDER=$(BUILDER))

endif #close IN_DOCKER
# Run the build inside the container
run_docker: build_docker
	$(BUILDER) /bin/bash

# Build target inside the container
%: build_docker
	@$(BUILDER) $(MAKE_CMD)



#limit need to dev
#1. mismatch user kali and ubuntu
#2. can not compile because get permision error using gcc to build inside container


