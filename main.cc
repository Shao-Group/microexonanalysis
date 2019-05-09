#include <iostream>
#include <fstream>
#include <sstream>
#include "item.h"
#include "transcript.h"
#include "genome.h"
#include <map>

int main(){
  std::string test = "/Users/isaacthomas/research/shao/annotations/test.sorted.gtf";
  std::string path = "/Users/isaacthomas/research/shao/annotations/Homo_sapiens.GRCh38.95.sorted.gtf";
  std::string results_path = "/Users/isaacthomas/research/shao/microexon_classifier/results.csv";
  std::string dist_path = "/Users/isaacthomas/research/shao/microexon_classifier/dist.csv";
  genome g(path);
  std::fstream rout, dout;
  rout.open(results_path);
  rout << "gene,transcript,exon length,start,end" << std::endl;
  PI32 *prev = NULL, *curr = NULL, *next = NULL;
  std::string gene_id, transcript_id;
  
  std::map<int, int> freqs;
  for(int i=1; i <=30; ++i){
    freqs[i] = 0;
  }

  for (int i=0; i < g.genes.size(); ++i){
    for (int j = 0; j < g.genes[i].transcripts.size(); ++j){
      gene_id = g.genes[i].transcripts[j].gene_id;
      transcript_id = g.genes[i].transcripts[j].transcript_id;
      for (int k=1; k < g.genes[i].transcripts[j].exons.size()-1; ++k){
        prev = &g.genes[i].transcripts[j].exons[k-1];
        curr = &g.genes[i].transcripts[j].exons[k];
        next = &g.genes[i].transcripts[j].exons[k+1];
        int start = curr->first;
        int end = curr->second;
        int length = end-start;
        //end of frame is exclusive
        if (length <= 30 && length > 0){
          //case 1
          int startl = prev->first;
          int endl = prev->second;
          int startr = next->first;
          int endr = next->second;
          //check if end of previous exon occurs before beginning of current exon
          //and end of current exon occurs before beginning of next exon
          if (endl < start && end < startr){
            freqs[length]++;
            rout << gene_id << "," << transcript_id << "," << length << "," << start << "," << end << std::endl;
          }

        } 

      }
    }
  }

  rout.close();

  dout.open(dist_path);
  dout << "exon length,exon frequency" << std::endl;
  for(int i=1; i < 30; ++i){
    dout << i << "," << freqs[i] << std::endl; 
  }
  dout.close();

  return 0;
}
