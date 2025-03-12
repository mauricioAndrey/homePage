entrada = input("Uma distância em metros: ")
print("A medida de {:.1f}m corresponde a".format(float(entrada))
      ,"\n{}km\n{}hm\n{}dam\n{}dm\n{}cm\n{}mm\n"
      .format(float(entrada)/1000, float(entrada)/100, 
              float(entrada)/10, float(entrada)*10, 
              float(entrada)*100, float(entrada)*1000))