//XOR cipher

fn xor_cypher_ui() -> i32{
    println!("XOR Cypher");
    println!("Please enter a string to encrypt:");
    let mut line = String::new();
    match std::io::stdin().read_line(&mut line) {
        Ok(_) => {
            println!("You entered: {}", line);
        }
        Err(error) => {
            println!("Error reading line {}", error);
        }
    }
    println!("Please enter a key:");
    let mut key = String::new();
    match std::io::stdin().read_line(&mut key) {
        Ok(_) => {
            println!("You entered: {}", key);
        }
        Err(error) => {
            println!("Error reading line {}", error);
        }
    }
    let outp = xor_encrypt(&line, &key);
    println!("Encrypted: {}", outp);
    println!("Length: {}", outp.len());
    return 0;
}


fn xor_encrypt<'a>(s: &'a str, t: &'a str) -> &'a str {
    let mut outp = String::with_capacity(s.len());
    let mut i = 0;
    for c in s.chars() {
        let c2 = t.chars().nth(i).unwrap();
        let c3 = c ^ c2;
        outp.push(c3);
        i += 1;
    }
    return &outp;
}