FROM alpine:latest
RUN apk add --no-cache bash curl
RUN curl -sSL https://gist.githubusercontent.com/aguag/d7c030f939f69b07784a309889b8510a/raw/lgdock.sh -o /usr/local/bin/lgdock && \
    curl -sSL https://gist.githubusercontent.com/aguag/83c887ef78610842508b9f972130d3e1/raw/lgdock_socat.sh -o /usr/local/bin/lgdock_socat && \
    chmod +x /usr/local/bin/lgdock* 
#ENTRYPOINT ["/usr/local/bin/lgdock"]
#ENTRYPOINT ["ls && tail -f /dev/null"]
CMD ["tail", "/dev/null"]
