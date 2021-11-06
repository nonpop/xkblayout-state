FROM alpine:3.14.2 AS build
RUN apk add --no-cache g++ libx11-dev make
WORKDIR /repo
COPY . .
RUN make
# RUN make && chmod a+x ./xkblayout-state
# Export to a minimal runtime image and run as an unprivileged user.
FROM alpine:3.14.2
RUN apk add --no-cache libstdc++ libx11
USER 1000:1000
WORKDIR /repo
COPY --from=build --chown=1000:1000 /repo/xkblayout-state .
ENTRYPOINT ["./xkblayout-state"]
