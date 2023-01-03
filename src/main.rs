use std::io;


mod ui;

fn terminal_test() -> i32 {
    println!("Hello, world! (from terminal_test) Please enter a line:");

    let stdin = io::stdin();

    let mut line = String::new();
    match stdin.read_line(&mut line) {
        Ok(_) => {
            print!("You entered: {}", line);
        }
        Err(error) => {
            print!("Error reading line {}", error);
        }
    }
    

    return 0;
}

fn main() {
    println!("Hello, world!");

    let mut app = ui::ConsoleApp::new();
    app.register_program("Terminal Test", terminal_test);

    app.run();
}
