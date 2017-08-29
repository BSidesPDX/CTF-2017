# export project_ID="your google platform project ID"
PROJECT_ID?= testing-bsidespdx-ctf-2017
REGISTRY := gcr.io
DOCKER_IMAGE := leek

.PHONY: container push test

CONTAINER_TAG := ${REGISTRY}/${PROJECT_ID}/${DOCKER_IMAGE}

target: container push deploy serve

deleteAll: delete deleteKube

# Docker Configurations

container:
	docker build --no-cache --tag ${CONTAINER_TAG} src

push: 
	gcloud docker -- push ${CONTAINER_TAG}

test:
	gcloud docker -- pull ${CONTAINER_TAG}
	gcloud container images list --repository ${REGISTRY}/${PROJECT_ID}

delete:
	gcloud container images delete ${CONTAINER_TAG}

# Kubernetes

deploy:
	kubectl create -f deployment/deploy.yaml

serve:
	kubectl create -f deployment/service.yaml

deleteKube:
	kubectl delete -f deployment/deploy.yaml
	kubectl delete -f deployment/service.yaml
