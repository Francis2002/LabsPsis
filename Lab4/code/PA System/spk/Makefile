CC = gcc
LDFLAGS = -lzmq  # Link against ZeroMQ library

all: pa_speaker

pa_speaker: pa_speaker.c
	$(CC) pa_speaker.c -o spk $(LDFLAGS)