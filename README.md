# BSidesPDX CTF 2017

| Challenge Name | Category | Points |
|----------------|----------|--------|
| DoNotTrek | Web | 100 |
| SeaQuell | Web | 200 |
| MakeIcon v20.16.37.17 | Web | 300 |
| Monolith | Web | 400 |
| ARM Wrestle | Shellcode | 100 |
| DasRücklauf | Shellcode | 500 |
| HTTPSH | Pwn | 100 |
| leek | Pwn | 200 |
| xordoz | Reversing | 100 |
| lostIT | Reversing | 200 |
| dotp33k | Reversing | 300 | 

# Local Testing & Deployment 

To locally test and deploy challenges with Docker, run the following after adding to docker-compose.yml

1. `docker-compose build && docker-compose up -d`
1. Containers are viewable at localhost:PORT (view with docker-compose ps)
1. `docker-compose kill` to stop the containers 
