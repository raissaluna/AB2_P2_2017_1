setwd(dir = "~/Git_Projects/AB2_P2_2017_1/Plotagem")
data <- read.table("out.txt")

col2 <- data[,2]
col3 <- data[,3]

x <- 1:length(col2)

plot(x,col2, type='l', ylim=c(min(col2,col3),max(col2,col3)))
points(col3, type='l', col='red', lty=2)


setwd(dir = "~/Git_Projects/AB2_P2_2017_1/Plotagem")
data <- read.table("out.txt")

col2 <- data[,2]
col3 <- data[,3]
col1 <- data[,1]

plot(col1,col3, type='l', ylim=c(min(col2,col3),max(col2,col3)))
lines(col1,col2,col='green')