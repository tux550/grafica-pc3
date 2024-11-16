# Define the source file and target directories
SHARED_ROOT = shared
MESH_FOLDER = mesh
JSON_LIB_FILE = json.h
DOCKER_FILE = Dockerfile
MAKE_FILE = Makefile
GITIGNORE_FILE = .gitignore
TARGET_DIRS = $(shell find . -type d -name 'exercise*')

update:
	@echo "Updating all the exercises..."
	@for dir in $(TARGET_DIRS); do \
		echo "Updating $$dir"; \
		rm -rf $$dir/$(MESH_FOLDER); \
		rm $$dir/$(DOCKER_FILE); \
		rm $$dir/$(MAKE_FILE); \
		rm $$dir/$(GITIGNORE_FILE); \
		rm $$dir/$(JSON_LIB_FILE); \
		cp -r $(SHARED_ROOT)/$(MESH_FOLDER) $$dir; \
		cp $(SHARED_ROOT)/$(DOCKER_FILE) $$dir; \
		cp $(SHARED_ROOT)/$(MAKE_FILE) $$dir; \
		cp $(SHARED_ROOT)/$(GITIGNORE_FILE) $$dir; \
		cp $(SHARED_ROOT)/$(JSON_LIB_FILE) $$dir; \
	done

test:
	@for dir in $(TARGET_DIRS); do \
		echo "Testing $$dir"; \
		cd $$dir; \
		make test; \
		if [ $$? -eq 0 ]; then \
			echo "PASSED $$dir!"; \
		else \
			echo "FAILED $$dir!"; \
			exit 1; \
		fi; \
		cd ..; \
	done

clean:
	@find . -name "*.out" -type f -delete
	@echo "All .out files have been deleted."