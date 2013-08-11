filename = "/Users/alexhum49/Documents/Workspace/CVA/CVATools/Output/FinalSpot.csv"

simul = read.csv(filename,header=FALSE)

# plot data to see if the acquisition is correct
plot(simul$V1, simul$V2)
names(simul)[2] <- "payoff"
names(simul)[1] <- "und"
res = lm(simul$payoff~simul$und)

summary(res)
help(lm)
res$coefficients[2]
abline(res)

library(MASS)
help(lm.ridge)
#data(payoff)
# does not work yet
resridge = lm.ridge(payoff ~ .,simul,lambda=seq(0,10,by=0.1))

data

# get inspire by this following code
data(longley) # not the same as the S-PLUS dataset
names(longley)[1] <- "y"
lm.ridge(y ~ ., longley)
plot(lm.ridge(y ~ ., longley, lambda = seq(0,0.1,0.001)))
select(lm.ridge(y ~ ., longley, lambda = seq(0,0.1,0.0001)))