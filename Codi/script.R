
source("params.R")

colors <- rainbow(numNs)

# --------------------------------------------- Model RBG

#load RBG output data
dataRBG <- vector("list",numNs)
i <- 1
while(i <= numNs)
{
	dataRBG[[i]] <- read.table(paste("outputRBG", ns[[i]], ".txt", sep = ""), sep = "\t", header = FALSE)
	i = i+1
}

#probability of being connected plot
png('plotRBGc.png');
plot(1, xlim = c(aini, afin), ylim = c(0.0, 1.0), type = "n", xlab = "constant <a>", ylab = "probability of being connected")
i <- 1
while(i <= numNs)
{
	xteo <- (log(ns[[i]])/ns[[i]])*ns[[i]]
	nea <- which.min(abs(dataRBG[[i]]$V1 - xteo))
	ymos <- dataRBG[[i]]$V2[[nea]]
	lines(dataRBG[[i]]$V1, dataRBG[[i]]$V2, type = "l", col = colors[[i]])
	points(xteo, ymos, pch = 19)
	i = i+1
}
legend("bottomright", legend = paste("n = ", ns, sep = ""), col = colors, cex = 0.8, lty = 1:1)
dev.off()

#size of largest connected component/total size + variance plot
png('plotRBGd.png');
plot(1, xlim = c(aini, afin), ylim = c(0.0, 1.0), type = "n", xlab = "constant <a>", ylab = "size of largest connected component/total size")
i <- 1
while(i <= numNs)
{
	xteo <- (1/(ns[[i]]-1))*ns[[i]]
	nea <- which.min(abs(dataRBG[[i]]$V1 - xteo))
	ymos <- (dataRBG[[i]]$V3[[nea]]-1)/(ns[[i]]-1)
	lines(dataRBG[[i]]$V1, (dataRBG[[i]]$V3-1)/(ns[[i]]-1), type = "l", col = colors[[i]])
	points(xteo, ymos, pch = 19)
	i = i+1
}
legend("bottomright", legend = paste("n = ", ns, sep = ""), col = colors, cex = 0.8, lty = 1:1)
dev.off()

#radius plot
png('plotRBGe.png');
plot(1, xlim = c(aini, afin), ylim = c(0.0, ns[[numNs]]/20), type = "n", xlab = "constant <a>", ylab = "diameter of largest connected component")
i <- 1
while(i <= numNs)
{
	lines(dataRBG[[i]]$V1, dataRBG[[i]]$V4, type = "l", col = colors[[i]])
	i = i+1
}
legend("topright", legend = paste("n = ", ns, sep = ""), col = colors, cex = 0.8, lty = 1:1)
dev.off()

# --------------------------------------------- Model RGG

#load RGG output data
dataRGG <- vector("list",numNs)
i <- 1
while(i <= numNs)
{
	dataRGG[[i]] <- read.table(paste("outputRGG", ns[[i]], ".txt", sep = ""), sep = "\t", header = FALSE)
	i = i+1
}

#probability of being connected plot
png('plotRGGc.png');
plot(1, xlim = c(bini, bfin), ylim = c(0.0, 1.0), type = "n", xlab = "constant <b>", ylab = "probability of being connected")
i <- 1
while(i <= numNs)
{
	xteo <- sqrt((log(ns[[i]])/log(2))/(pi*ns[[i]]))*ns[[i]]
	nea <- which.min(abs(dataRGG[[i]]$V1 - xteo))
	ymos <- dataRGG[[i]]$V2[[nea]]
	lines(dataRGG[[i]]$V1, dataRGG[[i]]$V2, type = "l", col = colors[[i]])
	points(xteo, ymos, pch = 19)
	i = i+1
}
legend("bottomright", legend = paste("n = ", ns, sep = ""), col = colors, cex = 0.8, lty = 1:1)
dev.off()

#size of largest connected component/total size plot
png('plotRGGd.png');
plot(1, xlim = c(bini, bfin), ylim = c(0.0, 1.0), type = "n", xlab = "constant <b>", ylab = "size of largest connected component/total size")
i <- 1
while(i <= numNs)
{
	xteo <- (1.44/sqrt(ns[[i]]))*ns[[i]]
	nea <- which.min(abs(dataRGG[[i]]$V1 - xteo))
	ymos <- (dataRGG[[i]]$V3[[nea]]-1)/(ns[[i]]-1)
	lines(dataRGG[[i]]$V1, (dataRGG[[i]]$V3-1)/(ns[[i]]-1), type = "l", col = colors[[i]])
	points(xteo, ymos, pch = 19)
	i = i+1
}
legend("bottomright", legend = paste("n = ", ns, sep = ""), col = colors, cex = 0.8, lty = 1:1)
dev.off()

#radius plot
png('plotRGGe.png');
plot(1, xlim = c(bini, bfin), ylim = c(0.0, ns[[numNs]]/12), type = "n", xlab = "constant <b>", ylab = "diameter of largest connected component")
i <- 1
while(i <= numNs)
{
	lines(dataRGG[[i]]$V1, dataRGG[[i]]$V4, type = "l", col = colors[[i]])
	i = i+1
}
legend("topright", legend = paste("n = ", ns, sep = ""), col = colors, cex = 0.8, lty = 1:1)
dev.off()

# --------------------------------------------- Aux

png('plotRBGdA.png');
plot(1, xlim = c(aini, sqrt(afin)), ylim = c(0.0, 1.0), type = "n", xlab = "constant <a>", ylab = "size of largest connected component/total size")
i <- 1
while(i <= numNs)
{
	xteo <- (1/(ns[[i]]-1))*ns[[i]]
	nea <- which.min(abs(dataRBG[[i]]$V1 - xteo))
	ymos <- (dataRBG[[i]]$V3[[nea]]-1)/(ns[[i]]-1)
	lines(dataRBG[[i]]$V1, (dataRBG[[i]]$V3-1)/(ns[[i]]-1), type = "l", col = colors[[i]])
	points(xteo, ymos, pch = 19)
	i = i+1
}
legend("bottomright", legend = paste("n = ", ns, sep = ""), col = colors, cex = 0.8, lty = 1:1)
dev.off()
