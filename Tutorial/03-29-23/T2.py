#Implementar una funcion que verifique si una lista esta ordenada de forma que represente un heap 

def is_heap(array):
    for i in range(0,len(array)):
        if array[i] < array[2*i+1] or array[i] < array[2*i+2]:
            return False
    return True
