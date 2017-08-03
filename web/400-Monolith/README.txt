#to prepare the environemnt:
download https://www.rfc-editor.org/in-notes/tar/RFC-all.tar.gz and extract to ./rfc/
run makeIndex.py > index.txt

#build the executable:
run build.sh

#build and upload the container:
../../makechroot.sh container.sh web400
docker import -c "ENTRYPOINT /rfcsearch" web400.tgz us.gcr.io/<YOUR-PROJECT-NAME>/web400

#edit the image: in the deployment.yaml to match <YOUR-PROJECT-NAME>
#then deploy the container to the cluster:
kubectl create -f deployment.yaml 
kubectl create -f service.yaml



