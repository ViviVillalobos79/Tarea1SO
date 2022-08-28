FROM ubuntu:latest
RUN apt update -y 
RUN apt install build-essential -y
RUN apt-get install libcurl4-openssl-dev -y
COPY . /Tarea1SO-main
WORKDIR Tarea1SO-main
RUN gcc cliente.c -lm -o cliente
CMD ["./cliente"]
