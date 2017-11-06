v <- read.csv("testando.csv")

par(bg="gray93")

plot(v$List,type = "l", col="red",xlab = "tamanho da ABB",
     ylab = "comparações", main = "List vs ABB")

lines(v$ABB, type = "l", col = "blue")