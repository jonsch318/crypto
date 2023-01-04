//XOR cipher

use crate::ui::program_selection::ProgramSelecton;


pub(crate) fn xor_cypher_ui() -> i32{
    let mut selection = ProgramSelecton::new("XOR Cypher");
    selection.register_program_unpacked("Encrypt", xor_encrypt_ui);
    selection.register_program_unpacked("Decrypt", xor_decrypt_ui);

    selection.run();
    return 0;
}

fn xor_encrypt_ui() -> i32 {
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

fn xor_decrypt_ui() -> i32 {
    println!("Decreption not implemented yet.");
    return 0;
}

fn xor_encrypt(s: &str, t: &str) -> String {
    let mut output = String::with_capacity(s.len());
    let mut i = 0;
    for c in s.chars() {
        let c2 = t.chars().nth(i).unwrap();
        let c3 = c as u32 ^ c2 as u32;
        output.push(char::from_u32(c3).unwrap());
        i += 1;
    }
    return output;
}