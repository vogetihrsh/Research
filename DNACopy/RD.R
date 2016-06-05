library("readDepth")
rdo = new("rdObject")
rdo = readDepth(rdo)
rdo.mapCor = rd.mapCorrect(rdo, minMapability=0.75)
rdo.mapCor.gcCor = rd.gcCorrect(rdo.mapCor)
segs = rd.cnSegments(rdo.mapCor.gcCor)
writeAlts(segs, rdo)
writeThresholds(rdo)

