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
    
    hexa="0x"
    split=line.replace("\n","")
    split=line.split(" ")
    print(split)
    if split[0] in BCC :
        print('ça BCC ici ou quoi')
        hexa+=BCC[split[0]]
        
        
    elif split[0] in opcode :
        print("ça opcode ici ou quoi")
        hexa+="0"
        if "R" not in split[3].upper():
            hexa+="1"
        else:
            hexa+="0"
        hexa+=opcode[split[0]]
        hexa+=split[2][1]
        hexa+=split[3][1]
        hexa+=split[1][1]
        
    
    print(hexa)
    