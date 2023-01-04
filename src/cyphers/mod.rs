use crate::ui::program_selection::ProgramSelecton;

pub mod xor;

pub fn cypher_selection_ui() -> i32 {

    let mut selection = ProgramSelecton::new("Cypher Selection");
    selection.register_program_unpacked("XOR Cypher", xor::xor_cypher_ui);

    selection.run();
    
    return 0;
}