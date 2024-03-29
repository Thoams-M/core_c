import re
import sys

if len(sys.argv)<2:
    print("Aucun fichier passé en argument (mettre chemin relatif)")
    exit()
else :
    fichier=sys.argv[1]

with open(fichier,"r") as code :
    program = code.readlines()
    code.close()
print("-------------------------------------------------------\n")
print("Lecture des instructions \n") 

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
print("-------------------------------------------------------\n")
print("Traduction des instructions \n")
for line in program :
    ##Formatage
    split=line.replace("\n","")
    split=line.split(" ")
    for i in range (0,len(split)):
        split[i]=split[i].rstrip()
        split[i]=split[i].replace(",","")
        

    if split[0] in BCC :

        hexa=BCC[split[0]]                             ##Brench
        if int(split[1])>0:                             ##signe décalage
            hexa+="0"                                   
        else :
            hexa+="1"
        
        hexa+=(format(abs(int(split[1])),"06x"))               ##Valeur
        
        
    elif split[0] in opcode :
        
        hexa="0"                                       ##brench
        if split[0]=="MOV":
            if "R" not in split[2].upper():             ##IV flag
                hexa+="1"
            else:
                hexa+="0"
            hexa+=opcode[split[0]]                      ##Opcode
            hexa+="0"                                   ##Opérende 1
            if "R" not in split[2].upper():             ##Opérende 2
                hexa+="0"
            else:
                hexa+=format(int(re.sub("[^0-9]","",split[2])),"x")
            hexa+=format(int(re.sub("[^0-9]","",split[1])),"x")                                   ##dest
            if "R" not in split[2].upper():                              ##IV
                if int(split[2]) <=15:
                    hexa+="0"
                    hexa+=format(int(re.sub("[^0-9]","",split[2])),"x")
                else :
                    
                    hexa+=format(int(re.sub("[^0-9]","",split[2])),"x")
            else:
                hexa+="00"
        else:
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
    hexa=(int(hexa,16))
    
    with open("sauvegarde.bin","ab") as output:
        
        output.write(hexa.to_bytes(4,'big'))
        output.close()
print("-------------------------------------------------------\n")
print("Ecriture des instruction dans sauvegarde.bin \n")
print("-------------------------------------------------------\n")
print("Compilation terminé\n")
