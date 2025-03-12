entrada = (input("Digite um numero: "))
if entrada.isnumeric():
    print("O antecessor de {} é {} e o sucessor é {}".format(entrada, (int(entrada)-1), (int(entrada)+1)))
else:
    print("Isso nem é número")
    