Module Lattice Based Key Encapsulation Mechanism (ML-KEM) implementation in Rust

Used to establish a shared secret key over a public channel (Alternative to DH that is resistant to quantum computers)

The secret established can be used with symmetric key cryptography algorithms, to perform encryption and authentication. 

The security of ML-KEM is related to the computational difficulty of the Module learning with Errors problem. 

Keys sizes range from 512, 768 to 1024 bits. 


# Steps

1. Alice generates a decapsulation key and an encapsulation key.

2. Alice keeps the decapsulation key private and makes tge encapsulation key available to Bob. 

3. Bob uses Alice's encapsulation key to generate a copy of a shared secret along with an associated cipher text. 

4. Bob sends the cipher text to Alice. 

5. Finally, Alice ses the cipher text from Bob along with ALice's private decapsulation key to compute anther copy of the shared secret.

