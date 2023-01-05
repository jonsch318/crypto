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
    
    for c in outp.chars() {
        print!("{} {}", c as u32, c);
    }

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

    print!("s: ");
    for s_char in s.chars() {
        print!("{} ({})", s_char as u32, s_char);
    }

    print!("\n t:");
    for t_char in t.chars() {
        print!("{} ({})", t_char as u32, t_char);
    }


    for s_char in s.chars() {
        let t_char = t.chars().nth(i).unwrap();
        let result = (s_char as u32) ^ (t_char as u32);
        
        let ascii = to_ascii(result);
        for c in ascii {
            output.push(c);
        }

        i = (i+1) % t.len();
    }
    return output;
}

fn to_ascii(s: u32) -> [char; 4] {

    let c1 = (s >> 24) as u8;
    let c2 = (s >> 16) as u8;
    let c3 = (s >> 8) as u8;
    let c4 = s as u8;

    let mut out = [0 as char; 4];
    out[0] = c1 as char;
    out[1] = c2 as char;
    out[2] = c3 as char;
    out[3] = c4 as char;
    return out;
}