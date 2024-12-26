import random
def generate_prime(bits):
    while True:
        n = random.getrandbits(bits)
        if n % 2 != 0:
            prime = True
            for i in range(3, int(n ** 0.5) + 1, 2):
                if n % i == 0:
                    prime = False
                    break
            if prime:
                return n

def generate_keypair(bits):
    p = generate_prime(bits)
    q = generate_prime(bits)
    while q == p:
        q = generate_prime(bits)
    N = p * q
    phi = (p - 1) * (q - 1)
    e = 65537
    d = modinv(e, phi)
    return ((N, e), (N, d))

def modinv(e, phi):
    d, x1, x2, y1 = 0, 0, 1, 1
    temp_phi = phi

    while e > 0:
        temp1 = temp_phi
        temp2 = temp_phi - temp1 * e
        temp_phi = e 
        e = temp2

        x = x2 - temp1 * x1
        y = d - temp1 * y1
        x2 = x1
        x1 = x
        d = y1
        y1 = y
    
    if temp_phi == 1:
        return d + phi
    