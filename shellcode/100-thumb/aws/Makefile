REGISTRY := bsidespdx
DOCKER_IMAGE := shellcode100

CONTAINER_TAG := ${REGISTRY}/${DOCKER_IMAGE}

target: container push deploy serve

clean: deleteDocker deleteKube

# Docker Configurations

container:
	docker build --no-cache --tag ${CONTAINER_TAG} ../src

push: 
	docker push ${CONTAINER_TAG}

# Kubernetes

deploy:
	cat deployment/deploy.yaml | kubectl create --context bsides-challenges-ns  -f -

serve:
	kubectl create --context bsides-challenges-ns -f deployment/service.yaml

deleteKube:
	cat deployment/deploy.yaml | kubectl delete --context bsides-challenges-ns -f -
	kubectl delete --context bsides-challenges-ns -f deployment/service.yaml
