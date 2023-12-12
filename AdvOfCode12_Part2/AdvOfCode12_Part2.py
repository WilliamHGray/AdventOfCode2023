from functools import cache

#NOTE: [:i] means from start to i not including i
#      but [i:] means from i to end including i

@cache
def isPossible(report, springs):

    if len(springs)==0:
        for r in report:
            if(r == '#'):
                return 0
        return 1

    totalSpring = 0
    for i in springs:
        totalSpring+=i
    if len(report) < totalSpring:
        return 0

    if report[0] == '.':  
        return isPossible(report[1:],springs) 

    current = 0
    nextTest = 0
    possible = True
    for r in report[:springs[0]]:
        if r=='.':
            possible = False
    if (len(report) > springs[0] and report[springs[0]]=='#'):
        possible = False

    if possible:
        current = isPossible(report[(springs[0] + 1):], springs[1:])      
    
    if report[0] == '?':
        nextTest = isPossible(report[1:], springs) 

    return current + nextTest



part1=0
part2=0
file = open ('AOC12.txt','r')
lines = file.read().splitlines()
for line in lines:
    report = line.split()[0]
    springs = tuple(map(int,line.split()[1].split(','))) 
    part1 += isPossible(report,springs)
    reportPart2 = report + '?' + report + '?' + report + '?' + report + '?' + report
    springsPart2 = springs + springs + springs + springs + springs
    part2 += isPossible(reportPart2,springsPart2)
print("Part 1 : ", part1)
print("Part 2 : ", part2)
   

