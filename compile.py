import re

with open("code.s","r") as code :
    program = code.readlines()
    code.close()
    

BCC = {
    "B": "8",
    "BEQ": "9",
    "BNE": "a",
    "BLE": "b",
    "BGE": "c",
    "BL": "d",
    "BG": "e"
    
}

opcode = {
    "AND": "0",
    "ORR": "1",
    "EOR": "2",
    "ADD": "3",
    "ADC": "4",
    "CMP": "5",
    "SUB": "6",
    "SBC": "7",
    "MOV": "8",
    "LSH": "9",
    "RSH": "a"
}

for line in program :
    ##Formatage
    hexa="0x"
    split=line.replace("\n","")
    split=line.split(" ")
    for i in range (0,len(split)):
        split[i]=split[i].rstrip()
        split[i]=split[i].replace(",","")
        
    
    if split[0] in BCC :

        hexa+=BCC[split[0]]                             ##Brench
        if int(split[1])>0:                             ##signe décalage
            hexa+="0"                                   
        else :
            hexa+="1"
        hexa+=(format(abs(int(split[1])),"x"))               ##Valeur
        
        
    elif split[0] in opcode :

        hexa+="0"                                       ##brench
        if split[0]=="CMP":
                                                        ##IV flag
            if "R" not in split[2].upper():
                hexa+="1"
            else:
                hexa+="0"
            hexa+=opcode[split[0]]                      ##Opcode
            hexa+=format(int(re.sub("[^0-9]","",split[1])),"x")         ##Opérende 1
                                                        ##Opérende 2 
            if "R" not in split[2].upper():
                hexa+="0"
            else:
                hexa+=format(int(re.sub("[^0-9]","",split[2])),"x")
            hexa+="0"                                   ##dest
            if "R" not in split[2].upper():             ##IV
                if int(split[2]) <=15:
                    hexa+="0"
                    hexa+=format(int(re.sub("[^0-9]","",split[2])),"x")
                else :
                    hexa+=format(int(re.sub("[^0-9]","",split[2])),"x")
            else:
                hexa+="00"
        else :     
            if "R" not in split[3].upper():             ##IV flag
                hexa+="1"
            else:
                hexa+="0"
            hexa+=opcode[split[0]]                      ##Opcode
            hexa+=format(int(re.sub("[^0-9]","",split[2])),"x")          ##Opérende 1
            if "R" not in split[3].upper():                              ##Opérende 2
                hexa+="0"
            else:
                hexa+=format(int(re.sub("[^0-9]","",split[3])),"x")

            hexa+=format(int(re.sub("[^0-9]","",split[1])),"x")          ##dest     
            if "R" not in split[3].upper():                              ##IV
                if int(split[3]) <=15:
                    hexa+="0"
                    hexa+=format(int(re.sub("[^0-9]","",split[3])),"x")
                else :
                    
                    hexa+=format(int(re.sub("[^0-9]","",split[3])),"x")
            else:
                hexa+="00"
        
    with open("a.out","a") as output:
        output.write(hexa+"\n")
        output.close()