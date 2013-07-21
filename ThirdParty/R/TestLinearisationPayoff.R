filename = "/Users/alexhum49/Documents/Workspace/CVA/CVATools/ThirdParty/R/Data/FinalSpot.csv"

data = read.csv(filename,header=FALSE)
payoff = rep(0,length(data[,1]))

for (i in 1:length(data[,1]))
{
  payoff[i] = max(data[i,1] - 1, 0)
}

# plot data to see if the acquisition is correct
plot(data[,1], payoff)

res = lm(payoff~data[,1])

summary(res)
abline(res)