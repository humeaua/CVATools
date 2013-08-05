install.packages("copula")
library("copula")

mycopula.clayton = archmCopula(family = "clayton", dim = 2, param = 2)
clayton = rCopula(mycopula.clayton, n=1000)

plot(clayton , col = "green")

mycopula.frank = archmCopula(family = "frank", dim = 2, param = 2)
frank = rCopula(mycopula.frank, n= 1000)
par(new= TRUE)
plot(frank, col = "red")


mycopula.gumbel = archmCopula(family = "gumbel", dim = 2, param = 2)
gumbel = rCopula(mycopula.gumbel, n= 1000)
par(new= TRUE)
plot(gumbel, col = "blue")
