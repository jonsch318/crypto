pub mod program_selection;

pub struct ConsoleApp {
    title: String,
    program_selection: program_selection::ProgramSelecton,
}

pub struct Program {
    name: String,
    func: fn() -> i32
}

impl Program {
    pub fn new(name: String, func: fn() -> i32) -> Program {
        Program {
            name: name,
            func: func
        }
    }

    pub fn run(&self) -> i32{
        (self.func)()
    }
}




impl ConsoleApp {
    pub fn new() -> ConsoleApp {
        let app = ConsoleApp {
            title: String::from("ConsoleApp"),
            program_selection: program_selection::ProgramSelecton::new("Main Menu"),
        };
        return app;
    }

    pub fn register_program(&mut self, name: &str, func: fn() -> i32) {
        let program = Program::new(name.to_string(), func);
        self.program_selection.register_program(program);
    }

    pub fn run(&self) {
        println!("Booting up {}...", self.title);

        self.program_selection.run();
    }
}