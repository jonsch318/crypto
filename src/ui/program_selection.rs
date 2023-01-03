use std::collections::HashMap;
use super::{Program};


pub struct ProgramSelecton {
    pub name: String,
    pub registered_programs: HashMap<String, Program>,
}


fn exit() -> i32 {
    println!("Exiting...");
    return 0;
}

fn program_showcase_wrapper() -> i32 {
    0
} 

fn program_showcase(selection: &ProgramSelecton) -> i32 {
    println!("Registered Programs:");

    for (_, program) in &selection.registered_programs {
        println!(" - {}", program.name);
    }

    return 0;
}


impl ProgramSelecton {
    pub fn new(name: &str) -> ProgramSelecton {
        let mut selection = ProgramSelecton {
            name: name.to_string(),
            registered_programs: HashMap::new()
        };

        selection.register_program_unpacked("Exit", exit);
        selection.register_program_unpacked("Help", program_showcase_wrapper);
        

        return selection;
    }

    pub fn register_program_unpacked(&mut self, name: &str, func: fn() -> i32) {
        let program = Program::new(name.to_string(), func);
        self.registered_programs.insert(name.to_string().to_lowercase(), program);
    }

    pub fn register_program(&mut self, program: Program) {
        self.registered_programs.insert(program.name.to_string().to_lowercase(), program);
    }

    pub fn run(&self) {
        println!("Please Select Program a Program (help for Help) | {} | ...", self.name);

        loop {
            println!("Enter program name to run:");
            let mut line = String::new();
            match std::io::stdin().read_line(&mut line) {
                Ok(_) => {
                    let program = self.registered_programs.get(&line.trim().to_string().to_lowercase());
                    match program {
                        Some(program) => {
                            println!("Running Program {} \n", program.name);
                            program.run();
                        }
                        None => {
                            println!("Program not found: {}", line.trim().to_string().to_lowercase());
                        }
                    }

                    if line.trim().to_lowercase() == "exit" {
                        return;
                    }

                    if line.trim().to_lowercase() == "help" {
                        program_showcase(self);
                    }

                }
                Err(error) => {
                    println!("Error reading line {}", error);
                }
            }
            println!("");
        }

    }
}
