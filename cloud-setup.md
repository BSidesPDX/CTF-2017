# How to play

Install prereqs:
https://cloud.google.com/sdk/docs/quickstart-debian-ubuntu

Log on to the GCP console.

Create a new cluster (5 micro nodes, for example)

Follow the Details->Connect To Cluster instructions to run "kubectl proxy"

Now the kubectl commands should work and you can launch deployments and services on this cluster


Notes: To firewall the cloud services on GCP, edit the yaml for the service. After type: LoadBalancer, add:

```
   loadBalancerSourceRanges:
     - <cidr>
     - <cidr>
```

Where cidr can be <ip>/32 for a single host.


# CLI

## Make a project

gcloud projects create testing-bsidespdx-ctf-2017 --name testing-bsidespdx-ctf-2017 
gcloud config set project testing-bsidespdx-ctf-2017

## Make a cluster

gcloud container clusters create testing-bsidespdx-ctf-2017 --zone us-west1-a --num-nodes 5
gcloud config set container/cluster testing-bsidespdx-ctf-2017
