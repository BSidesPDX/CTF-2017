# export project_ID="your google platform project ID"
PROJECT_ID ?= testing-bsidespdx-ctf-2017
REGISTRY := gcr.io
DOCKER_IMAGE := nodes

CONTAINER_TAG := ${REGISTRY}/${PROJECT_ID}/${DOCKER_IMAGE}

target: container push deploy server

clean: deleteDocker deleteKube
	make -C src clean

# Docker Configurations

container:
	make -C src
	docker build --no-cache --tag ${CONTAINER_TAG} src

push: 
	gcloud docker -- push ${CONTAINER_TAG}

deleteDocker:
	gcloud container images delete ${CONTAINER_TAG}

# Kubernetes

deploy:
	cat deployment/deploy.yaml | sed 's/\%PROJECT_ID\%/${PROJECT_ID}/g' | kubectl create -f -

serve:
	kubectl create -f deployment/service.yaml

deleteKube:
	cat deployment/deploy.yaml | sed 's/\%PROJECT_ID\%/${PROJECT_ID}/g' | kubectl delete -f -
	kubectl delete -f deployment/service.yaml
