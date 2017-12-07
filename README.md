# BSidesPDX CTF 2017

Challenges built by: [TTimzen](https://twitter.com/TTimzen) & [pwnpnw](https://twitter.com/pwnpnw)

Infrastructure support provided by: [yalam96](https://twitter.com/yalam96), [andrewkrug](https://twitter.com/andrewkrug), [CornflakeSavage](https://twitter.com/CornflakeSavage).

Infrastructure: [Bsides-Infra](https://github.com/flamingspaz/bsides-infra)

## Challenges

| Challenge Name | Category | Points | Port |
|----------------|----------|--------|------|
| DoNotTrek | Web | 100 | 5000 |
| SeaQuell | Web | 200 | 8000 |
| MakeIcon v20.16.37.17 | Web | 300 | 80 |
| Monolith | Web | 400 | 5001 |
| Tiny Thumb | Shellcode | 100 | 31337 |
| MOV On | Shellcode | 200 | 35264 |
| UniMIPS | Shellcode | 300 | 41414 |
| DasRücklauf | Shellcode | 400 | 5050 |
| Cookies | Pwn | 100 | 53000 |
| leek | Pwn | 200 | 2007 |
| nodes | Pwn | 300 | 4321 |
| 2048 | Pwn | 400 | 2048 |
| xordoz | Reversing | 100 | NA |
| lostIT | Reversing | 200 | NA |
| dotp33k | Reversing | 300 | NA |
| 2ez400 | Reversing | 400 | NA |

All flags are in "/flag"

## Local Deployment

To locally test, deploy or play challenges with Docker, run the following (Ubuntu)

1. `sudo apt install gcc-multilib gcc-mipsel-linux-gnu gcc-arm-linux-gnueabi g++-multilib linux-libc-dev:i386`
1. `make`
1. `docker-compose build && docker-compose up -d`
1. Containers are viewable at localhost:PORT (view with docker-compose ps)
1. `docker-compose kill` to stop the containers
1. `make clean` to clean the source folders

## GCP

You can also deploy via GCP and run the challenges in k8s. All of this is in `category/challenge/Makefile` to deploy.

## BSidesPDX

CTF was ran during [BSidesPDX 2017](https://bsidespdx.org/events/2017/contests-events.html) on October 20th and 21st.

We used [CTFd](https://ctfd.io/) for the scoreboard hosted at [BSidesPDXCTF.party](https://bsidespdxctf.party/).

`category/challenge/aws/Makefile` was used to deploy to a k8s pod in AWS. We had intended to use the GCP deployment and moved to this by creating our own cluster with the help from the above infra supporters.
